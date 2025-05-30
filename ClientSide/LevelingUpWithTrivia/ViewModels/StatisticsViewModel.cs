using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class StatisticsViewModel : ObservableObject
    {
        [RelayCommand]
        private void NavToMain()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new MainMenuView();
        }

        [RelayCommand]
        private void NavToUserStatistics()
        {
            var windowModel = MainWindowViewModel.Current!;
            windowModel.Content = new UserStatisticsView();
        }

        [RelayCommand]
        private void NavToHighScores()
        {
            var windowModel = MainWindowViewModel.Current!;
            windowModel.Content = new HighScoresView();
        }
    }
}
