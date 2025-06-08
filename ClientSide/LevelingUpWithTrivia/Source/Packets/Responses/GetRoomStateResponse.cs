namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record GetRoomStateResponse(
        int Status,
        bool HasGameBegun,
        List<string> Players,
        int QuestionCount,
        int AnswerTimeOut
    ) : Response(113);
}