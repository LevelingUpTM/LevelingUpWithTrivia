using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public class GetHighScoreResponse
    {
        public int Status { get; set; }
        public List<string> Statistics { get; set; }
    }
}
