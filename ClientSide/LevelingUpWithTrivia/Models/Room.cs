using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Models
{
    public class Room
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int MaxPlayers { get; set; }
        public int QuestionCount { get; set; }
        public int TimePerQuestion { get; set; }
        public bool IsActive { get; set; }
    }
}
