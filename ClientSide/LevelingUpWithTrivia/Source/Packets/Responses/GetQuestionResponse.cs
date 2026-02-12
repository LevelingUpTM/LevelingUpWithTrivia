using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record GetQuestionResponse(
        int Status,
        string Question,
        Dictionary<string, string> Answers
    ) : Response(116);
}
