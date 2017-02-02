interface IApplication {
    //アプリケーションの開始時に呼ばれる．この中でwhileループしたりすることは望ましくない．
    void Start();
    //アプリケーションの終了時に呼ばれる．
    void Quit();
    //アプリケーションが動作中に毎フレーム呼ばれる．
    void Update();
    //アプリケーションの終了時，Quitの前に呼ばれる．後始末などを書きたいときに．正常終了は0
    int Cleanup();
    //アプリケーションの動作中juliusからwordが入ってくる．
    //wordはjulius側で定義する(ex.入力「こんにちは」word=hello)
    void Order(String word);
    //アプリケーション側はここをfalseにすると自発的に終われる
    boolean IsRunning();
}
