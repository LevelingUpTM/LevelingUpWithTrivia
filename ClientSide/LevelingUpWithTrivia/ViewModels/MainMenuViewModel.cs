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
        public void NavToInfo()
        {
            var windowModel = MainWindowViewModel.Current!;
            windowModel.Content = new InfoView();
        }
    }
}
