using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record GetPlayersInRoomResponse(
        List<string> players
    ) : Response(101);

}
