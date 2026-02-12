using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record SubmitAnswerResponse(
        int Status,
        int CorrectAnswerId
    ) : Response(117);
}
