using LevelingUpWithTrivia.ViewModels;
using System.Windows.Controls;

namespace LevelingUpWithTrivia.Views
{
    public partial class WaitingRoomView : UserControl
    {
        public WaitingRoomView(int roomId, string roomName, bool isHost)
        {
            InitializeComponent();
            DataContext = new WaitingRoomViewModel(roomId, roomName, isHost);
        }
    }
}
