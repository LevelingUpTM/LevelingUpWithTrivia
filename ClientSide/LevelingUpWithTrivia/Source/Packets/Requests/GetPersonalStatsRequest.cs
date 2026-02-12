using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Requests
{
    public record GetPersonalStatsRequest(
    ) : Request(8);
}