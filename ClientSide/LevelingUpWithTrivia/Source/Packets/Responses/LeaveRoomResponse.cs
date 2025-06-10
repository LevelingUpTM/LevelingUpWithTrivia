using LevelingUpWithTrivia.Source;

namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record LeaveRoomResponse(
        int Status
    ) : Response(114);
}