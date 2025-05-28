using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Views;
using System.Windows;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class JoinRoomViewModel : ObservableObject
    {
        [ObservableProperty]
        private int roomId;

        [RelayCommand]
        private void JoinRoom()
        {
            var request = new JoinRoomRequest(RoomId);
            Communicator.Instance.Send(request);
            var response = Communicator.Instance.Receive();

            if (response is JoinRoomResponse joinRoomResponse && joinRoomResponse.Status == 0)
            {
                MessageBox.Show("Successfully joined the room!");
                    //get room name from server
                MainWindowViewModel.Current!.Content = new WaitingRoomView(RoomId, "Room #" + RoomId, false);
            }
            else
            {
                MessageBox.Show($"Join failed.\nResponse type: {response.GetType().Name}");
                if (response is JoinRoomResponse jrr)
                    MessageBox.Show($"JoinRoomResponse.Status = {jrr.Status}");
            }
        }

        [RelayCommand]
        private void Back()
        {
            MainWindowViewModel.Current!.Content = new MainMenuView();
        }
    }
}