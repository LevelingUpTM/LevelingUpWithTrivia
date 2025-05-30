using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record GetPersonalStatsResponse(
        int Status,
        List<string> Statistics
    ) : Response(109);
}
