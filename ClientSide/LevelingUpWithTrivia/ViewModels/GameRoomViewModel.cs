using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using LevelingUpWithTrivia.Source;
using LevelingUpWithTrivia.Source.Packets.Requests;
using LevelingUpWithTrivia.Source.Packets.Responses;
using LevelingUpWithTrivia.Views;
using System.Windows;
using System.Windows.Threading;


namespace LevelingUpWithTrivia.ViewModels
{
    public partial class GameRoomViewModel : ObservableObject
    {
        [ObservableProperty] private string currentQuestion = "";
        [ObservableProperty] private string answer1 = "";
        [ObservableProperty] private string answer2 = "";
        [ObservableProperty] private string answer3 = "";
        [ObservableProperty] private string answer4 = "";

        [ObservableProperty] private int questionsLeft = 0;
        [ObservableProperty] private int correctAnswers = 0;
        [ObservableProperty] private int timeLeft = 0;

        private int totalQuestions = 0;
        private int timePerQuestion = 0;
        private DispatcherTimer timer;
        private DateTime questionStartTime;

        public GameRoomViewModel(int totalQuestions, int timePerQuestion)
        {
            this.totalQuestions = totalQuestions;
            this.timePerQuestion = timePerQuestion;
            this.questionsLeft = totalQuestions;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Timer_Tick;

            LoadNextQuestion();
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            TimeLeft--;
            if (TimeLeft <= 0)
            {
                timer.Stop();
                SubmitAnswer(-1, timePerQuestion);
            }
        }
  
        private void LoadNextQuestion()
        {
            try
            {
                var request = new GetQuestionRequest();
                Communicator.Instance.Send(request);
                var response = Communicator.Instance.Receive();

                if (response is GetQuestionResponse questionResponse && questionResponse.Status == 1)
                {
                    CurrentQuestion = questionResponse.Question;
                    Answer1 = questionResponse.Answers["0"];
                    Answer2 = questionResponse.Answers["1"];
                    Answer3 = questionResponse.Answers["2"];
                    Answer4 = questionResponse.Answers["3"];

                    TimeLeft = timePerQuestion;
                    questionStartTime = DateTime.Now;
                    timer.Start();
                }
                else
                {
                    MessageBox.Show("Failed to load question.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error loading question: " + ex.Message);
            }
        }

        [RelayCommand]
        public void SelectAnswer(string parameter)
        {
            if (!int.TryParse(parameter, out int answerId))
                return;

            var timeTaken = (int)(DateTime.Now - questionStartTime).TotalSeconds;
            timer.Stop();
            SubmitAnswer(answerId, timeTaken);
        }


        private void SubmitAnswer(int answerId, int answerTime)
        {
            try
            {
                var request = new SubmitAnswerRequest(answerId, answerTime);
                Communicator.Instance.Send(request);
                var response = Communicator.Instance.Receive();

                if (response is SubmitAnswerResponse submitResponse && submitResponse.Status == 1)
                {
                    if (submitResponse.CorrectAnswerId == answerId)
                    {
                        CorrectAnswers++;
                    }

                    QuestionsLeft--;

                    if (QuestionsLeft > 0)
                    {
                        LoadNextQuestion();
                    }
                    else
                    {
                        MessageBox.Show("Game finished!");
                        // TODO: navigate to result screen here.
                    }
                }
                else
                {
                    MessageBox.Show("Error submitting answer.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error submitting answer: " + ex.Message);
            }
        }

        [RelayCommand]
        public void LeaveRoom()
        {
            try
            {
                var request = new LeaveGameRequest();
                Communicator.Instance.Send(request);
                var response = Communicator.Instance.Receive();

                if (response is LeaveGameResponse leaveResponse && leaveResponse.Status == 1)
                {
                    MainWindowViewModel.Current!.Content = new MainMenuView();
                }
                else
                {
                    MessageBox.Show("Failed to leave room.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error leaving room: " + ex.Message);
            }
        }
    }
}

