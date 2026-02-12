using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Views;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class UserStatisticsViewModel : ObservableObject
    {
        [ObservableProperty] private ObservableCollection<string> statistics = new();
        
        [RelayCommand]
        private void NavToMain()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new MainMenuView();
        }
        [RelayCommand]
        private void LoadPersonalStats()
        {
            try
            {
                var request = new GetPersonalStatsRequest();
                Communicator.Instance.Send(request);

                var response = Communicator.Instance.Receive();

                if (response is GetPersonalStatsResponse personalStatsResponse)
                {
                    MessageBox.Show($"Response Status: {personalStatsResponse.Status}\nStats count: {personalStatsResponse.Statistics.Count}");

                    if (personalStatsResponse.Status == 0) // SUCCESS
                    {
                        Statistics.Clear();
                        foreach (var stat in personalStatsResponse.Statistics)
                        {
                            Statistics.Add(stat);
                        }
                    }
                    else
                    {
                        MessageBox.Show("Failed to load personal stats: Status code " + personalStatsResponse.Status);
                    }
                }
                else
                {
                    MessageBox.Show("Invalid response type from server: " + response.GetType().Name);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error loading stats: " + ex.Message);
            }
        }
    }
}