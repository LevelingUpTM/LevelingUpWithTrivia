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
    public partial class StartMenuViewModel : ObservableObject
    {
        [RelayCommand]
        private void NavToLogin()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new LogInView();
        }

        [RelayCommand]
        private void NavToSignup()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new SignUpView();
        }
    }
}
