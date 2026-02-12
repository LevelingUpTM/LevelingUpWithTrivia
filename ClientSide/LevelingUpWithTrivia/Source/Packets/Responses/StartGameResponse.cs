namespace LevelingUpWithTrivia.Source.Packets.Responses
{
    public record StartGameResponse(
        int Status    
    ) : Response(112);
}