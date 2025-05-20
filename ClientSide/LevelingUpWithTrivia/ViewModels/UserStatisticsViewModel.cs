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
    public partial class UserStatisticsViewModel : ObservableObject
    {
        [RelayCommand]
        private void NavToMain()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new MainMenuView();
        }
    }
}
