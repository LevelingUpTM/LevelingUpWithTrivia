using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;

namespace LevelingUpWithTrivia.Source.Packets
{
    public static class RequestSerializer
    {
        public static byte[] SerializeRequest<T>(T requestObject, byte requestCode)
        {
            string json = JsonSerializer.Serialize(requestObject);

            byte[] jsonBytes = Encoding.UTF8.GetBytes(json);
            int length = jsonBytes.Length;

            List<byte> buffer = new List<byte>();

            buffer.Add(requestCode);

            buffer.Add((byte)((length >> 24) & 0xFF));
            buffer.Add((byte)((length >> 16) & 0xFF));
            buffer.Add((byte)((length >> 8) & 0xFF));
            buffer.Add((byte)(length & 0xFF));

            buffer.AddRange(jsonBytes);

            return buffer.ToArray();
        }
    }
}
