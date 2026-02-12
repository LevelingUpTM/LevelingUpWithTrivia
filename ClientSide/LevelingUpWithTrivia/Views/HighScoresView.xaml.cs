using System.Windows.Controls;
using LevelingUpWithTrivia.ViewModels;

namespace LevelingUpWithTrivia.Views;

public partial class HighScoresView : UserControl
{
    public HighScoresView()
    {
        InitializeComponent();
        DataContext = new HighScoresViewModel();
    }
}