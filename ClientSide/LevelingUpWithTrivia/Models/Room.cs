using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Models
{
    public class Room
    {
        public int id { get; set; }
        public string name { get; set; }
        public int maxPlayers { get; set; }
        public int questionCount { get; set; }
        public int timePerQuestion { get; set; }
        public bool isActive { get; set; }
    }
}
