using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record GetHighScoreResponse(
        int Status,
        List<string> Statistics
    ) : Response(110);
}
