using LevelingUpWithTrivia.Models;
using LevelingUpWithTrivia.ViewModels;
using System.Windows.Controls;

namespace LevelingUpWithTrivia.Views
{
    public partial class WaitingRoomView : UserControl
    {
        public WaitingRoomView(Room room, string roomName, bool isHost)
        {
            InitializeComponent();
            DataContext = new WaitingRoomViewModel(room, roomName, isHost);
        }
    }
}
