namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record CloseRoomResponse(
        int Status
    ) : Response(111);
}