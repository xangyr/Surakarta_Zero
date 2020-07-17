\documentclass[10pt,twocolumn,letterpaper]{article}
\usepackage[utf8]{inputenc}
%\usepackage{algorithmic}
\usepackage[ruled,vlined]{algorithm2e}
\usepackage{graphicx}
\usepackage{hyperref}
%\usepackage{cvpr}
\usepackage{times}
\usepackage{epsfig}
\usepackage{amsmath}
\usepackage{amssymb}

\begin{document}

\twocolumn

\title{Preparing Monte Carlo Tree Search for Reinforcement Learning of Surakarta Game}
\author{Xiangyu Ren}
\date{July 2020}

\maketitle

\begin{abstract}

Reinforcement Learning is an important field of Machine Learning that trains AI to be more suitable for one and only one specific field in daily usage, such as chess games. A great example is the project from Google, AlphaGo Zero. In this work, we did the following: Write cpp based MCTS programs, and modified rollout policy and weights of attack moves to increase efficiency of MCTS AI; Rebuild MCTS in python for implementing reinforcement learning and neural networks following the extremely-randomly-pick policy of MCTS. 

\end{abstract}

\section{Introduction}

\subsection{Monte Carlo Tree Search}

Monte Carlo Tree Search (MCTS) is a well-known and successful algorithm of searching when implementing on board games, has been proven by AlphaGo Zero. In past years, Teams from Google, who wrote AlphaGo, used AlphaGo to beat world players in Chess Go, even mastered it at the end. Since MCTS is a relatively independent algorithm, we don’t need to change the code for implementing it on different games. When implementing MCTS, searching trees are built recursively in a loop, and we have 4 steps for each searching: select, expand, simulate, backpropagate. 

MCTS  uses an important factor UCT to balance between exploration and exploitation. c here is set to $\sqrt{2}$.
$$UCT=\frac{w_i}{n_i}+c\frac{\sqrt{\ln N_i}}{n_i}$$

So to implement MCTS on Surakarta, at first we create a root node for the MCTS tree. Then expand the root node with all potential moves from current state as children node. See Figure~\ref{fig:root}.

\begin{figure}[h]
    \centering
    \includegraphics[width=8cm]{./figure/root_ex}
    \caption{Expanding the root}
    \label{fig:root}
\end{figure}

Since all children nodes aren't visited, we select the first node, plus 1 to visit count of the node, and do simulation following specified rollout policy: randomly choose from current player's potential moves then swap player until game is in terminal state, then return and update to all parent nodes 1 if AI wins, 0 if loses. Take wins as an example, See Figure~\ref{fig:update}.

\begin{figure}[h]
    \centering
    \includegraphics[width=8cm]{./figure/update}
    \caption{Simulation and Backpropagation}
    \label{fig:update}
\end{figure}

After visited all leaf nodes, the MCTS tree with $\displaystyle{\frac{w_i}{n_i}}$ labeled might look like Figure~\ref{fig:mid}. Then compute UCT of every node to decide which node to select and expand. 

\begin{figure}[h]
    \centering
    \includegraphics[width=8cm]{./figure/mid}
    \caption{}
    \label{fig:mid}
\end{figure}
\noindent
We can get following equations: 

for the First node,$$UCT_1=1+c\sqrt{\frac{\ln{3}}{1}}$$

for the Second node, $$UCT_2=0+c\sqrt{\frac{\ln{3}}{1}}$$

and for the Third node. $$UCT_3=1+c\sqrt{\frac{\ln{3}}{1}}$$

Depends on maximizing UCT, select the first node again, and we expand the node with potential moves. All expanded nodes aren't visited, select the first leaf node and do simulation.

Starting from the root node, Compute and Maximize UCT again. Third child node of the root node has max UCT this time, See Figure~\ref{fig:exmore}. Select the node and expand. 

The 4 processes will keep looping until hit the preset terminal stage, in this project, it's 1600 times.

\begin{figure}[h]
    \centering
    \includegraphics[width=8cm]{./figure/ex_more}
    \caption{}
    \label{fig:exmore}
\end{figure}

\subsection{Multi-threading Monte Carlo Tree Search}

MCTS is easier to be implemented with multi-thread than other traditional tree search algorithms, such as alpha-beta algorithm, because of its own 4 separate processes.  Also, programs running on python are relatively slow on its efficiency. With an idea of parallel search, implementing MCTS with multi-threading properly set up can increase the efficiency by at least 30\%. 

An possible approach is to add buffers to the MCTS using pipeline. With the MCTS algorithm introduced in Section 1.1, instead of simulate for one leaf node, simulate for all leaf node of the selected node which has the max UCT. 

\section{Implementation}

\subsection{Working on MCTS using cpp}

While preparing MCTS using cpp for Reinforcement Learning, we met the following problems. 

\begin{enumerate}
    \item When we exactly followed the policy of MCTS, which is to randomly choose potential moves when simulating, the MCTS AI performs badly -- couldn’t even win a rookie to the game. 
    
\end{enumerate}

For the first problem, we modify our rollout policy, which is used in the simulation process, to randomly pick potential attack moves first, then other potential moves. Also, we change the weight of the UCT of attack moves by multiplying 1.4 when AI is making its final move. With these two changes, the AI performs more aggressive and a little smarter, however it still has 47\% percent of losing rate when competing with other Surakarta AIs, See Figure~\ref{fig:rate}. 

\begin{figure}[h]
    \centering
    \includegraphics[width=8cm]{./figure/chart}
    \caption{MCTS AI vs. Other Surakarta AIs}
    \label{fig:rate}
\end{figure}

We also add a destroy function to free memory of the tree that was built when the function terminated to avoid any memory leaks.

\subsection{Datasets input for Reinforcement Learning}

In the dataset for each game, it has 17 boards and a list of UCTs of all potential moves for each round of the game, which is each chess play in our project. See Figure~\ref{fig:board}, A has 1 board to determine the side: a 6$\times$6 matrix filled with 1 or -1; B has 8 enemy's history boards: eight 6$\times$6 matrices filled with 1 and 0; C has 8 AI's history boards: eight 6$\times$6 matrices filled with 1 and 0. So we wrote an output function to write in datas each round. Starting from the initial state, which is when the game begin, We initialized the stack with one identity board and 2 eight-same boards\\

\noindent
$\begin{bmatrix}
  1 & 1 & 1 & 1 & 1 & 1\\ 
  1 & 1 & 1 & 1 & 1 & 1\\
  0 & 0 & 0 & 0 & 0 & 0\\
  0 & 0 & 0 & 0 & 0 & 0\\
  0 & 0 & 0 & 0 & 0 & 0\\
  0 & 0 & 0 & 0 & 0 & 0
\end{bmatrix}$ and 
$\begin{bmatrix}
  0 & 0 & 0 & 0 & 0 & 0\\
  0 & 0 & 0 & 0 & 0 & 0\\
  0 & 0 & 0 & 0 & 0 & 0\\
  0 & 0 & 0 & 0 & 0 & 0\\
  1 & 1 & 1 & 1 & 1 & 1\\ 
  1 & 1 & 1 & 1 & 1 & 1
\end{bmatrix}$.

At each play, push or insert the latest board into the stack. If the size of one side is over 8, pop that oldest board from that side.


\begin{figure}[h]
    \centering
    \includegraphics[width=8cm]{./figure/board}
    \caption{17 boards in dataset}
    \label{fig:board}
\end{figure}

\subsection{Migrating MCTS to python}

We let MCTS AI self play a few games, and generate the datasets we need, we found that 

\begin{enumerate}
    \item We misunderstood Reinforcement Learning and confused with Supervised Learning
\end{enumerate}

For this problem, with our previous understanding of Reinforcement Learning, which is actually Supervised Learning, using the old setup of the neural networks can only give us an approximately same performance of the provided AI, might increase the time efficiency but not make the AI more intelligent or play better on Surakarta game. So we migrate the MCTS to python, rewrite it following the randomly-pick rollout policy, rebuild the policy setup of the neural networks and train it using Google Cloud Service. 

\begin{thebibliography}{}
\bibitem{UCT}
Levente Kocsis, Csaba Szepesv{\'a}ri, Jan Willemson.
\textit{Improved Monte-Carlo Search}
MTA SZTAKI, Kende u. 13-17, Budapest, Hungary, 2006.

\bibitem{mul_mcts}
Markus Enzenberger and Martin Muller.
\textit{A Lock-free Multithreaded Monte-Carlo Tree Search Algorithm}
Department of Computing Science, University of Alberta, 2009.

\bibitem{rl}
S. Gelly.
\textit{A Contribution to Reinforcement Learning; Application to Computer-Go}
PhD thesis, Universite Paris-Sud, 2007.

\bibitem{pa_mcts}
S. Ali Mirsoleimani, Aske Plaat, Jaap van den Herik and Jos Vermaseren.
\textit{Structured Parallel Programming for Monte CarloTree Search}
Leiden Centre of Data Science, Leiden University, 2017.

\bibitem{lf_mcts}
S. Ali Mirsoleimani,Jaap van den Herik, Aske Plaat and Jos Vermaseren.
\textit{A Lock-free Algorithm for Parallel MCTS}
Leiden Centre of Data Science, Leiden University, 2018.

\end{thebibliography}

\end{document}
