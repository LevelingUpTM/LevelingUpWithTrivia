using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Requests
{
    public record CreateRoomRequest(
        string RoomName,
        int MaxUsers,
        int QuestionCount,
        int AnswerTimeout
    ) : Request(7);

}
