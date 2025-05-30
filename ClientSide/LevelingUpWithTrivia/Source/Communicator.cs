using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;
using LevelingUpWithTrivia.Source.Packets.Requests;
using System.Text.Json;
using LevelingUpWithTrivia.Source.Packets.Responses;

namespace LevelingUpWithTrivia.Source
{
    public class Communicator
    {
        public static Communicator Instance { get; } = new();
        private TcpClient? _client;
        private NetworkStream? _stream;
        private Communicator() { }
        public void Connect(string ip = "127.0.0.1", int port = 5555)
        {
            _client = new TcpClient();
            _client.Connect(IPAddress.Parse(ip), port);
            _stream = _client.GetStream();
        }
        public void Send<T>(T request) where T : Request
        {
            if (_stream == null || !_stream.CanWrite)
                throw new InvalidOperationException("Not connected to server.");

            byte[] data = RequestSerializer.SerializeRequest(request);
            
            _stream.Write(data, 0, data.Length);
        }
        public Response Receive()
        {
            if (_stream == null || !_stream.CanRead)
                throw new InvalidOperationException("Not connected to server.");

            byte[] header = new byte[5];
            ReadExact(_stream, header, 5);

            byte messageCode = header[0];
            int length = (header[1] << 24) | (header[2] << 16) | (header[3] << 8) | header[4];

            byte[] body = new byte[length];
            ReadExact(_stream, body, length);

            string json = Encoding.UTF8.GetString(body);

            return ResponseDeserializer.DeserializeResponse(messageCode, json);
            
            
        }
        public void Close()
        {
            _stream?.Close();
            _client?.Close();
        }

        private static void ReadExact(NetworkStream stream, byte[] buffer, int size)
        {
            int offset = 0;
            while (offset < size)
            {
                int read = stream.Read(buffer, offset, size - offset);
                if (read == 0)
                    throw new IOException("Disconnected from server.");
                offset += read;
            }
        }
    }
}
