using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;

namespace LevelingUpWithTrivia.Source.Packets.Requests
{
    public static class RequestSerializer
    {
        public static byte[] SerializeRequest<T>(T requestObject) where T : Request
        {
            string json = JsonSerializer.Serialize(requestObject, new JsonSerializerOptions
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
            });

            byte[] jsonBytes = Encoding.UTF8.GetBytes(json);
            int length = jsonBytes.Length;

            List<byte> buffer = new List<byte>();

            buffer.Add(requestObject.Code);

            buffer.Add((byte)(length >> 24 & 0xFF));
            buffer.Add((byte)(length >> 16 & 0xFF));
            buffer.Add((byte)(length >> 8 & 0xFF));
            buffer.Add((byte)(length & 0xFF));

            buffer.AddRange(jsonBytes);

            return buffer.ToArray();
        }
    }
}
