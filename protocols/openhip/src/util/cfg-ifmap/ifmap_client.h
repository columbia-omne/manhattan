/* -*- Mode:cc-mode; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/* vim: set ai sw=2 ts=2 et cindent cino={1s: */
/*
 * Host Identity Protocol
 * Copyright (c) 2011-2012 the Boeing Company
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *  \file  ifmap_client.h
 *
 *  \authors	David Mattes, <david.mattes@boeing.com>
 *
 *  \brief  IF-MAP Plug-in for Endbox mode: MAP Client class declaration
 *
 */

#ifndef IFMAP_CLIENT_H
#define IFMAP_CLIENT_H

#include <QtCore>
#include "ifmap1_1.h"

using namespace ifmap11;

class IfmapClient : public QObject {
  Q_OBJECT
public:
  IfmapClient(QObject *parent = 0);
  ~IfmapClient();

public slots:
  void connectToMap(QMap<QString,QString> *mapConfig);
  void setUnderlayIp(QString ip);

private slots:
  void newSession();
  void mapResponseOnARC(MapResponse *mapResponse);
  void publishUnderlayIp();

private:
  void updateEndboxMapping(SearchResult *searchResult);
  QString interfaceAddr();
  bool purgePublisher();
  bool publishCurrentState();
  bool setupEndboxMapSubscriptions();
  bool searchCurrentConfig();
  void processPollResponse(MapResponse *mapResponse);

private:
  Ifmap *_ifmap;
  bool _haveValidSession;
  QString _sessionId;
  QString _publisherId;
  QString _currentIp;
  QString _oldIp;
  bool _haveInitialConfig;

  QString _scadaNS;

  QString _matchLinks;
  QString _resultsFilter;
  int _maxDepth;

  int _retryDelay;

  QMap<QString,QString> _mapConfig;
};

#endif
