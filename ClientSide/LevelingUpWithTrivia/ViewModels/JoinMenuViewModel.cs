using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Views;


namespace LevelingUpWithTrivia.ViewModels
{
    public partial class JoinMenuViewModel : ObservableObject
    {
        [RelayCommand]
        private void NavToMain()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new MainMenuView();
        }
    }
}
