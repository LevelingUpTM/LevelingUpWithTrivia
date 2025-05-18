using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public static class ResponseDeserializer
    {
        public static object DeserializeResponse(byte[] packet)
        {
            // First byte = response code
            byte responseCode = packet[0];

            // Next 4 bytes = length
            int length = (packet[1] << 24) | (packet[2] << 16) | (packet[3] << 8) | packet[4];

            // Remaining bytes = JSON
            string json = Encoding.UTF8.GetString(packet, 5, length);

            return responseCode switch
            {
                101 => JsonSerializer.Deserialize<LoginResponse>(json),
                102 => JsonSerializer.Deserialize<SignupResponse>(json),
                103 => JsonSerializer.Deserialize<ErrorResponse>(json),
                104 => JsonSerializer.Deserialize<LogoutResponse>(json),
                105 => JsonSerializer.Deserialize<GetRoomsResponse>(json),
                106 => JsonSerializer.Deserialize<GetPlayersInRoomResponse>(json),
                107 => JsonSerializer.Deserialize<JoinRoomResponse>(json),
                108 => JsonSerializer.Deserialize<CreateRoomResponse>(json),
                109 => JsonSerializer.Deserialize<GetPersonalStatsResponse>(json),
                110 => JsonSerializer.Deserialize<GetHighScoreResponse>(json),
                _ => throw new Exception("Unknown response code: " + responseCode),
            };
        }
    }
}
