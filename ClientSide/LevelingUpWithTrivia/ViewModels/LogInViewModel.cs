using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class LogInViewModel : ObservableObject
    {
        [ObservableProperty] private string username;
        [ObservableProperty] private string password;

        [RelayCommand]
        private void NavToSignup()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new SignUpView();
        }

        [RelayCommand]
        private void NavToMainMenu()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new MainMenuView();
        }

        [RelayCommand]
        private void LogIn()
        {
            try
            {
                var request = new LoginRequest(username, password);
                Communicator.Instance.Send(request);
                var response = Communicator.Instance.Receive();

                if (response is LoginResponse loginResponse)
                {
                    switch (loginResponse.Status)
                    {
                        case 1:
                            MessageBox.Show("Login successful!");
                            MainWindowViewModel.Current!.Content = new MainMenuView();
                            break;
                        case 2:
                            MessageBox.Show("Username not found.");
                            break;
                        case 3:
                            MessageBox.Show("Incorrect password.");
                            break;
                        case 4:
                            MessageBox.Show("User is already logged in.");
                            break;
                        default:
                            MessageBox.Show("Unexpected response.");
                            break;
                    }
                }
                else
                {
                    System.Windows.MessageBox.Show("Invalid response from server.");
                }
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show("Login failed: " + ex.Message);
            }
        }
    }
}
