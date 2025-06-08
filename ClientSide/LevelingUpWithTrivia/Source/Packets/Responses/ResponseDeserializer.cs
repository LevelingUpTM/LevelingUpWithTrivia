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
        public static Response DeserializeResponse(byte responseCode, string json)
        {
            return responseCode switch
            {
                101 => Deserialize<LoginResponse>(json)!,
                102 => Deserialize<SignupResponse>(json)!,
                103 => Deserialize<ErrorResponse>(json)!,
                104 => Deserialize<LogoutResponse>(json)!,
                105 => Deserialize<GetRoomsResponse>(json)!,
                106 => Deserialize<GetPlayersInRoomResponse>(json)!,
                107 => Deserialize<JoinRoomResponse>(json)!,
                108 => Deserialize<CreateRoomResponse>(json)!,
                109 => Deserialize<GetPersonalStatsResponse>(json)!,
                110 => Deserialize<GetHighScoreResponse>(json)!,
                113 => Deserialize<GetRoomStateResponse>(json)!,
                _ => throw new Exception("Unknown response code: " + responseCode),
            };
        }

        private static T Deserialize<T>(string json) where T : Response
        {
            return JsonSerializer.Deserialize<T>(json, new JsonSerializerOptions
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
            })!;
        }
    }
}
