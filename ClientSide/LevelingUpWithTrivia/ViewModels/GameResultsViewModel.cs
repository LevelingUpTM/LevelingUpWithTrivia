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
    public partial class GameResultsViewModel : ObservableObject
    {
        public partial class PlayerResult : ObservableObject
        {
            [ObservableProperty] private string username;
            [ObservableProperty] private int correctAnswers;
            [ObservableProperty] private int wrongAnswers;
            [ObservableProperty] private float averageAnswerTime;
        }

        [ObservableProperty] private ObservableCollection<PlayerResult> results = new();

        public void LoadGameResults(GetGameResultsResponse resultResponse)
        {
            Results.Clear();
            foreach (var player in resultResponse.Results)
            {
                Results.Add(new PlayerResult
                {
                    Username = player.Username,
                    CorrectAnswers = player.CorrectAnswerCount,
                    WrongAnswers = player.WrongAnswerCount,
                    AverageAnswerTime = player.AverageAnswerTime
                });
            }
        }

        [RelayCommand]
        private void BackToMain()
        {
            MainWindowViewModel.Current!.Content = new MainMenuView();
        }
    }
}
