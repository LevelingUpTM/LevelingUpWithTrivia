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
            else
            {
                _refreshTimer.Stop();
                MessageBox.Show("Room was closed by the host.");
                MainWindowViewModel.Current!.Content = new MainMenuView();
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
        private void PerformLeaveRoom()
        {
            if (IsHost)
            {
                CloseRoom();
            }
            else
            {
                LeaveRoom();
            }
        }

        private void LeaveRoom()
        {
            Communicator.Instance.Send(new LeaveRoomRequest());
            var response = Communicator.Instance.Receive();

            if (response is LeaveRoomResponse leaveRoomResponse && leaveRoomResponse.Status == 1)
            {
                _refreshTimer.Stop();
                MainWindowViewModel.Current!.Content = new MainMenuView();
            }
            else
            {
                MessageBox.Show("Failed to leave the room.");
                if (response is LeaveRoomResponse lrr)
                    MessageBox.Show($"LeaveRoomResponse.Status = {lrr.Status}");
                else
                    MessageBox.Show($"Unexpected response: {response.GetType().Name}");
            }
        }

        private void CloseRoom()
        {
            Communicator.Instance.Send(new CloseRoomRequest());
            var response = Communicator.Instance.Receive();
            if (response is CloseRoomResponse closeRoomResponse && closeRoomResponse.Status == 1)
            {
                _refreshTimer.Stop();
                MainWindowViewModel.Current!.Content = new MainMenuView();
            }
            else
            {
                MessageBox.Show("Failed to close the room.");
                if (response is CloseRoomResponse crr)
                    MessageBox.Show($"CloseRoomResponse.Status = {crr.Status}");
                else
                    MessageBox.Show($"Unexpected response: {response.GetType().Name}");
            }
        }
    }
}
