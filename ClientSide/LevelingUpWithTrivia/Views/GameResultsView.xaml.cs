using System.Windows.Controls;
using LevelingUpWithTrivia.ViewModels;

namespace LevelingUpWithTrivia.Views
{
    public partial class GameResultsView : UserControl
    {
        public GameResultsView()
        {
            InitializeComponent();
            DataContext = new GameResultsViewModel();
        }
    }
}