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
                //101 => JsonSerializer.Deserialize<LoginResponse>(json),
                102 => JsonSerializer.Deserialize<SignupResponse>(json)!,
                //103 => JsonSerializer.Deserialize<ErrorResponse>(json),
                //104 => JsonSerializer.Deserialize<LogoutResponse>(json),
                //105 => JsonSerializer.Deserialize<GetRoomsResponse>(json),
                //106 => JsonSerializer.Deserialize<GetPlayersInRoomResponse>(json),
                //107 => JsonSerializer.Deserialize<JoinRoomResponse>(json),
                //108 => JsonSerializer.Deserialize<CreateRoomResponse>(json),
                //109 => JsonSerializer.Deserialize<GetPersonalStatsResponse>(json),
                //110 => JsonSerializer.Deserialize<GetHighScoreResponse>(json),
                _ => throw new Exception("Unknown response code: " + responseCode),
            };
        }
    }
}
