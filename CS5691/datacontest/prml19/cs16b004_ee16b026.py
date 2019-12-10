#!/usr/bin/env python
# coding: utf-8

# In[ ]:


#import packages
import pandas as pd
import numpy as np
import scipy.sparse as sps
from sklearn.decomposition import PCA
from sklearn.svm import SVR


# In[ ]:


#read data
df_test = pd.read_csv("test.csv")
df_data = pd.read_csv('train.csv')
# df_train, df_valid = df_data.head(5000000), df_data.tail(len(df_data) -5000000)
df_validation = pd.read_csv('validation.csv')
df_validation = df_validation.drop(['timestamp'],axis = 1)
df_data = df_data.append(df_validation,ignore_index= True, sort = False)
df_data = df_data.sample(frac = 1)
train_data = df_data.values
# valid_data = df_valid.to_numpy()
test_data = df_test.values


# In[ ]:


m = int(np.max(train_data.T[0]))
n = int(np.max(train_data.T[1]))
r = np.zeros(shape=(m+1,n+1))
for i in range(len(train_data)):
  x1 = int(train_data.T[0][i])
  x2 = int(train_data.T[1][i])
  r[x1][x2] = train_data.T[2][i]


# In[ ]:


T = 20
mu1 = np.mean(train_data.T[2])
mu = 0
eta = 0.01
b_users = np.zeros(m+1)
b_movies  = np.zeros(n+1)
temp1 = np.zeros(m+1)
temp2 = np.zeros(n+1)
for i in range(T):
  batch_size = 128
  temp1 = b_users.copy()
  temp2 = b_movies.copy()
  n_batches = int(len(train_data)/(batch_size)) + 1
  for j in range(n_batches):
    batch = train_data[j*batch_size:(j+1)*batch_size]
    b1 = mu + b_users[batch.T[0].astype(int)] + b_movies[batch.T[1].astype(int)]
    b3 = b1.copy()
    b2 = batch.T[2]
    mu += eta*(np.sum(b2-b3))
    users = np.unique(batch.T[0].astype(int))
    movies = np.unique(batch.T[1].astype(int))
    for i in users:
      b_users[i] += eta*(np.sum((b2-b3)[np.where(batch.T[0] == i)[0]]))
    for i in movies:
      b_movies[i] += eta*(np.sum((b2-b3)[np.where(batch.T[1] == i)[0]])) 


# In[ ]:


mu1 = np.mean(train_data.T[2])
b = np.zeros(shape=(m+1,n+1))
for i in range(m+1):
  for j in range(n+1):
      if(b_users[i]!=0  or b_movies[j]!=0):
          b[i][j] = mu + b_users[i] + b_movies[j]

b1 = b.copy()


# In[ ]:


lambda1 = 100
a = r.copy()
a[a>0] = 1
temp = np.sum(r,axis =0)/np.sum(a,axis=0)
a_hat  = r -temp
a_hat = a_hat*a
corr = np.matmul(a_hat.T,a_hat)/(np.sqrt((np.matmul((a_hat**2).T,a))*(np.matmul(a.T,a_hat**2))))
corr[np.isnan(corr)] = 0


# In[ ]:


nij = np.matmul(a.T,a)
sim2 = np.zeros(shape=(n+1,n+1))
for i in range(n+1):
    for j in range(n+1):
        sim2[i][j] = corr[i][j]*nij[i][j]/(nij[i][j] + lambda1)


# In[ ]:



for K in [30]:
    r_hat = b1.copy()
    for i in range(len(test_data)):
        x1 = int(test_data.T[0][i])
        x2 = int(test_data.T[1][i])
        if(x1<=m and x2<=n):
            temp = np.where(a[x1]==1)[0]
            add = 0
            if(len(temp)>0):
                temp_movies = np.arange(n+1)[temp]
                keys = sim2[x2][temp_movies]
                vals = temp_movies
                x = np.argsort(abs(keys))[::-1]
                keys = keys[x][0:K]
                vals = vals[x][0:K]
                if(np.sum(keys)!=0):
                    for k,sim in enumerate(keys):
                        add+=(r[x1,vals[k]] - b1[x1,vals[k]])*sim
                    add = add/(np.sum(keys))
            r_hat[x1,x2] = b1[x1,x2] + add   


# In[ ]:


r_hat1 = r_hat.copy()
r_hat1[r_hat1<0.5] = 0.5
r_hat1[r_hat1>5] = 5


# In[ ]:



df_genome_scores = pd.read_csv('genome_scores.csv')
genome_scores = df_genome_scores.values
att = np.mean(genome_scores.T[2])
movie_features = np.full((9998,1128), att)
for i in range(len(genome_scores)):
    t1 = int(genome_scores[i][0])
    t2 = int(genome_scores[i][1]-1)
    movie_features[t1][t2] = genome_scores[i][2]
Y_train = np.sum(r,axis =0)/np.sum(a,axis=0)
Y_train[np.isnan(Y_train)] = 0
temp = np.where(Y_train != 0)[0]
Y_train = Y_train[temp]
X_train = np.zeros((n+1,1128))
for i in range(n+1):
    X_train[i] = movie_features[i]  
X_train = X_train[temp]
pca = PCA(n_components=200)
pca.fit(X_train)
X = pca.transform(X_train) 
movie_features_pca =  pca.transform(movie_features)


# In[ ]:



clf = SVR(C=1.0)
clf.fit(X,Y_train)
pred_svr = clf.predict(movie_features_pca)


# In[ ]:


from sklearn.svm import SVR
users = np.unique(test_data.T[0])
user_clf = np.empty(m+1,dtype=object)
user_matrix = np.zeros(shape=(m+1,1128))
for user in users:
    user = int(user)
    temp = np.where(r[user]!=0)[0]
    if(len(temp)>0):
        Y_train = r[user][temp]
        X_train = movie_features_pca[temp]
        clf = SVR(C=1.0)
        clf.fit(X_train,Y_train)
        user_clf[user] = clf


# In[ ]:


data = []
ind = 0
index = 0
for i in range(len(test_data)):
    x1 = int(test_data.T[0][i])
    x2 = int(test_data.T[1][i])
    try:
      t = r_hat1[x1,x2]
      temp = np.where(r[x1]!=0)[0]
      t = r_hat1[x1,x2]
      if(len(temp)>0):
          clf = user_clf[x1]
          t1 = clf.predict(movie_features_pca[x2].reshape(1,-1))
          t2 = t1*0.6+t*0.4
          t2 = float(t2)
          data.append([ind,round(min(5,max(0.5,t2)),1)])
      else:
          t = pred_svr[x2]
          data.append([ind,round(min(5,max(0.5,t)),1)])
    except:
        temp = np.where(r[x1]!=0)[0]
        if(len(temp)>0):
          clf = user_clf[x1]
          t1 = clf.predict(movie_features_pca[x2].reshape(1,-1))
          t1 = float(t1)
          t2 = t1*0.5 + pred_svr[x2]*0.5
          data.append([ind,round(min(5,max(0.5,t2)),1)])
        else:
          t = pred_svr[x2]
          data.append([ind,round(min(5,max(0.5,t)),1)])
    ind+= 1
df_test_pred = pd.DataFrame(data, columns = ['Id', 'Prediction'])
df_test_pred.to_csv('test_pred.csv',header=True, encoding='utf-8',index=False)

