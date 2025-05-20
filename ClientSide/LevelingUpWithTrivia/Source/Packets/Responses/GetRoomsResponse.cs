using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Generic;
using LevelingUpWithTrivia.Models;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record GetRoomsResponse(
        int Status,
        List<Room> rooms
    ) : Response(105);
}
