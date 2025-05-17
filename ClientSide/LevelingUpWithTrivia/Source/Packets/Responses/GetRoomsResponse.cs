using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Generic;
using LevelingUpWithTrivia.Models;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public class GetRoomsResponse
    {
        public int status { get; set; }
        public List<Room> rooms { get; set; }
    }
}
