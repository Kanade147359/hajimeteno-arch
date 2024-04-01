= 瑣末な情報

ひっかかったところを書き連ねていく

== 画像を横に並べる

@<href>{https://qiita.com/AyumuTakai/items/14c2d9172151103a6663}参考

Re:VIEWにはそんな機能はないのでlatexの組み込みコマンドで無理やり横に並べる

//emlist[]{

 //embed[latex]{
\begin{figure}[htbp]
  \begin{center}
    \begin{tabular}{c}

    \begin{minipage}{0.5\hsize}
      \begin{center}
 //}

 //image[apparel][洋服工場][scale=1.0]{
 //}


 //embed[latex]{
      \end{center}
    \end{minipage}
 //}
 
 //embed[latex]{
    \begin{minipage}{0.5\hsize}
      \begin{center}
 //}

 //image[food][食品工場の写真][scale=0.5]{
 //}

 //embed[latex]{
      \end{center}
    \end{minipage}
 //}

 //embed[latex]{
\end{tabular}
 \end{center}
\end{figure}
 //}

//}

== 改ページ

latexの機能を使う

//emlist[]{
 //embed[latex]{
 \clearpage
 //}
//}

== 右寄せ、左寄せ、中央揃え

latexの機能を使う。

//emlist[]{
 //embed[latex]{
\begin{flushright}
右寄せ
\end{flushright}
 //}

 //embed[latex]{
\begin{flushleft}
左寄せ
\end{flushleft}
 //}

 //embed[latex]{
\begin{center}
中央揃え
\end{center}
 //}
//}
