using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.Source.Packets.Requests
{
    public record LoginRequest(
    string Username,
    string Password
    ) : Request(1);
}
