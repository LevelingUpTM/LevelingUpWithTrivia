using LevelingUpWithTrivia.ViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace LevelingUpWithTrivia.Views
{
    public partial class InfoView : UserControl
    {
        public InfoView()
        {
            InitializeComponent();

            DataContext = new InfoViewModel();
        }
        private void GitLabLogo_Click()
        {
            Process.Start(new ProcessStartInfo("https://gitlab.com/Tomgluz/Trivia_Eliran_Maor_2025") {UseShellExecute = true });
        }

        private void YoutubeLogo_Click()
        {
            Process.Start(new ProcessStartInfo("https://www.youtube.com/watch?v=dQw4w9WgXcQ ") {UseShellExecute = true });
        }
    }
}
