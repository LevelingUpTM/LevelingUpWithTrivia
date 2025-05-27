using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Views;
using System.Collections.ObjectModel;
using System.Windows;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class WaitingRoomViewModel : ObservableObject
    {
        private readonly bool _isHost;

        [ObservableProperty]
        private string roomName;
        [ObservableProperty]
        private int _roomId;
        [ObservableProperty]
        private ObservableCollection<string> players = new();

        public bool IsHost => _isHost;

        public WaitingRoomViewModel(int roomId, string roomName, bool isHost)
        {
            _roomId = roomId;
            RoomName = roomName;
            _isHost = isHost;

            RefreshPlayers();
        }

        private void RefreshPlayers()
        {
            Communicator.Instance.Send(new GetPlayersInRoomRequest(_roomId));
            var response = Communicator.Instance.Receive();

            if (response is GetPlayersInRoomResponse playersResponse)
            {
                Players.Clear();
                foreach (var player in playersResponse.players)
                    Players.Add(player);
            }
        }

        [RelayCommand]
        private void StartGame()
        {
            if (!_isHost)
                return;

            // TODO: Add start game request logic here
            MessageBox.Show("Game started!");
        }

        [RelayCommand]
        private void LeaveRoom()
        {
            // Optional: send a leave-room request
            MainWindowViewModel.Current.Content = new MainMenuView();
        }
    }
}
