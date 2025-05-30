using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Views;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class CreateMenuViewModel : ObservableObject
    {
        [ObservableProperty]
        private string roomName;

        [ObservableProperty]
        private int maxPlayers;

        [ObservableProperty]
        private int questionCount;

        [ObservableProperty]
        private int timePerQuestion;

        [RelayCommand]
        public void CreateRoom()
        {
            if (string.IsNullOrWhiteSpace(RoomName) ||
                MaxPlayers <= 0 ||
                QuestionCount <= 0 ||
                TimePerQuestion <= 0)
            {
                MessageBox.Show("All fields must be filled and greater than 0.", "Validation Error", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }
            
            var request = new CreateRoomRequest(
                RoomName,
                MaxPlayers,
                QuestionCount,
                TimePerQuestion
            );

            Communicator.Instance.Send(request);
            var response = Communicator.Instance.Receive();

            if (response is CreateRoomResponse createRoomResponse && createRoomResponse.Status == 0)
            {
                // success
                MessageBox.Show("Room created successfully!");
                MainWindowViewModel.Current!.Content = new WaitingRoomView(createRoomResponse.RoomId, RoomName, true);
            }
            else
            {
                MessageBox.Show($"Unexpected response: {response.GetType().Name}");
                if (response is CreateRoomResponse crr)
                    MessageBox.Show($"LogoutResponse.Status = {crr.Status}");
                MessageBox.Show("An error occurred.");
            }
        }
        [RelayCommand]
        private void NavToMain()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new MainMenuView();
        }

        [RelayCommand]
        private void Back()
        {
            var windowModel = MainWindowViewModel.Current!;
            windowModel.Content = new MainMenuView();
        }
    }
}
