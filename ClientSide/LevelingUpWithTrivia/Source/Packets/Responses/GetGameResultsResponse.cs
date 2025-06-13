using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record PlayerResults(
        string Username,
        int CorrectAnswerCount,
        int WrongAnswerCount,
        float AverageAnswerTime
    );
    public record GetGameResultsResponse(
        int Status,
        List<PlayerResults> Results
    ) : Response(118);
}
