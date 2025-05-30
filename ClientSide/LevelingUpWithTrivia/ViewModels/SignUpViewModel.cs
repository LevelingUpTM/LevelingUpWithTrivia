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
    public partial class SignUpViewModel : ObservableObject
    {
        [ObservableProperty] private string username;
        [ObservableProperty] private string password;
        [ObservableProperty] private string email;
        [ObservableProperty] private string confirmPassword;

        [RelayCommand]
        private void NavToLogin()
        {
            var windowModel = MainWindowViewModel.Current!;
            windowModel.Content = new LogInView();
        }

        [RelayCommand]
        private void SignUp()
        {
            try
            {
                if (Password != ConfirmPassword)
                {
                    MessageBox.Show("Passwords do not match.");
                    return;
                }

                var request = new SignupRequest(username, password, email);
                Communicator.Instance.Send(request);
                var response = Communicator.Instance.Receive();

                if (response is SignupResponse signupResponse)
                {
                    switch (signupResponse.Status)
                    {
                        case 1:
                            MessageBox.Show("Signup successful!");
                            NavToLogin();
                            break;
                        case 2:
                            MessageBox.Show("Username already exists.");
                            break;
                        case 3:
                            MessageBox.Show("Unknown error during signup.");
                            break;
                        default:
                            MessageBox.Show("Unexpected response.");
                            break;
                    }
                }
                else
                {
                    MessageBox.Show("Invalid response from server.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Signup failed: " + ex.Message);
            }
        }
    }
}
