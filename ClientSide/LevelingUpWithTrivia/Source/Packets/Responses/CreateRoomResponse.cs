using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record CreateRoomResponse(
        int Status,
        int RoomId 
    ) : Response(108);
}
