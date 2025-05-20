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
    public partial class SignUpViewModel : ObservableObject
    {
        [RelayCommand]
        private void NavToLogin()
        {
            var windowModel = MainWindowViewModel.Current!;

            windowModel.Content = new LogInView();
        }
    }
}
