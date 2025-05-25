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
using LevelingUpWithTrivia.Models;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class MainMenuViewModel : ObservableObject
    {
        [RelayCommand]
        public void NavToJoin()
        {
            var windowModel = MainWindowViewModel.Current!;
            windowModel.Content = new JoinMenuView();
        }

        [RelayCommand]
        public void NavToCreate()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new CreateMenuView();
        }

        [RelayCommand]
        public void NavToStats()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new StatisticsView();
        }

        [RelayCommand]
        public void NavToUserStats()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new UserStatisticsView();
        }


        [RelayCommand]
        public void NavToInfo()
        {
            var windowModel = MainWindowViewModel.Current!;
            windowModel.Content = new InfoView();
        }

        [RelayCommand]
        public void NavToStart() 
        {
            try
            {
                var logoutRequest = new LogoutRequest(MainWindowViewModel.CurrentUser.Username);
                Communicator.Instance.Send(logoutRequest);

                var response = Communicator.Instance.Receive();

                if (response is LogoutResponse logoutResponse && logoutResponse.Status == 0)
                {
                    var windowModel = MainWindowViewModel.Current!;
                    windowModel.Content = new StartMenuView();
                }
                else
                {
                    Console.WriteLine($"Unexpected response: {response.GetType().Name}");
                    if (response is LogoutResponse lr)
                        Console.WriteLine($"LogoutResponse.Status = {lr.Status}");
                    MessageBox.Show("An error occurred.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Logout failed:" + ex.Message);
            }
        }
    }
}
