using System.Collections.ObjectModel;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Views;

namespace LevelingUpWithTrivia.ViewModels;

public partial class HighScoresViewModel : ObservableObject
{
        [ObservableProperty]
        ObservableCollection<string> statistics = new();

    [RelayCommand]
    private void NavToMain()
    {
        var windowModel = MainWindowViewModel.Current!;
        windowModel.Content = new MainMenuView();
    }

    [RelayCommand]
    private void LoadHighScores()
    {
        try
        {
            var request = new GetHighScoreRequest();
            Communicator.Instance.Send(request);

            var response = Communicator.Instance.Receive();

            if (response is GetHighScoreResponse highScoreResponse)
            {
                MessageBox.Show($"Response Status: {highScoreResponse.Status}\nStats count: {highScoreResponse.Statistics.Count}");

                if (highScoreResponse.Status == 0) // SUCCESS
                {
                    Statistics.Clear();
                    foreach (var stat in highScoreResponse.Statistics)
                    {
                        Statistics.Add(stat);
                    }
                }
                else
                {
                    MessageBox.Show("Failed to load high scores: Status code " + highScoreResponse.Status);
                }
            }
            else
            {
                MessageBox.Show("Invalid response type from server: " + response.GetType().Name);
            }
        }
        catch (Exception ex)
        {
            MessageBox.Show("Error loading high scores: " + ex.Message);
        }
    }
}

