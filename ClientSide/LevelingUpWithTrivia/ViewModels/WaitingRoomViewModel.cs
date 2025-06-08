using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Views;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Threading;

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
        private readonly DispatcherTimer _refreshTimer = new();

        public bool IsHost => _isHost;

        public WaitingRoomViewModel(int roomId, string roomName, bool isHost)
        {
            _roomId = roomId;
            RoomName = roomName;
            _isHost = isHost;

            _refreshTimer.Interval = TimeSpan.FromSeconds(2);
            _refreshTimer.Tick += (s, e) => RefreshPlayers();
            _refreshTimer.Start();
            
            RefreshPlayers();
        }

        private void RefreshPlayers()
        {
            Communicator.Instance.Send(new GetRoomStateRequest());
            var response = Communicator.Instance.Receive();

            if (response is GetRoomStateResponse roomState)
            {
                if (roomState.HasGameBegun)
                {
                    MessageBox.Show("Game has already started!");
                    return;
                }

                Players.Clear();
                foreach (var player in roomState.Players)
                {
                    Players.Add(player);
                }
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
            _refreshTimer.Stop();
            MainWindowViewModel.Current.Content = new MainMenuView();
        }
    }
}
