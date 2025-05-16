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
            // Get the active MainWindowViewModel
            var windowModel = MainWindowViewModel.Current!;

            // Set the window content to JoinMenuView
            windowModel.Content = new JoinMenuView();
        }
    }
}
