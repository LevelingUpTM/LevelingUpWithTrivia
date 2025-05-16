using CommunityToolkit.Mvvm.ComponentModel;
using LevelingUpWithTrivia.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace LevelingUpWithTrivia.ViewModels
{
    public partial class MainWindowViewModel : ObservableObject
    {
        public static MainWindowViewModel? Current => Application.Current.MainWindow.DataContext as MainWindowViewModel;

        [ObservableProperty]
        private UIElement content = new MainMenuView();
    }
}
