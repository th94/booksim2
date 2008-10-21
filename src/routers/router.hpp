#ifndef _ROUTER_HPP_
#define _ROUTER_HPP_

#include <string>
#include <vector>

#include "module.hpp"
#include "flit.hpp"
#include "credit.hpp"
#include "flitchannel.hpp"
#include "creditchannel.hpp"
#include "config_utils.hpp"

class Router : public Module {
protected:
  int _id;

  
  int _inputs;
  int _outputs;
 
  int _input_speedup;
  int _output_speedup;

  int _routing_delay;
  int _vc_alloc_delay;
  int _sw_alloc_delay;
  int _st_prepare_delay;
  int _st_final_delay;

  int _credit_delay;


  vector<FlitChannel *>   *_input_channels;
  vector<CreditChannel *> *_input_credits;
  vector<FlitChannel *>   *_output_channels;
  vector<CreditChannel *> *_output_credits;
  vector<bool>            *_channel_faults;

  Credit *_NewCredit( int vcs = 1 );
  void    _RetireCredit( Credit *c );

public:
  Router( const Configuration& config,
	  Module *parent, string name, int id,
	  int inputs, int outputs );

  virtual ~Router( );

  static Router *NewRouter( const Configuration& config,
			    Module *parent, string name, int id,
			    int inputs, int outputs );

  void AddInputChannel( FlitChannel *channel, CreditChannel *backchannel );
  void AddOutputChannel( FlitChannel *channel, CreditChannel *backchannel );
 


  virtual void ReadInputs( ) = 0;
  virtual void InternalStep( ) = 0;
  virtual void WriteOutputs( ) = 0;

  void OutChannelFault( int c, bool fault = true );
  bool IsFaultyOutput( int c ) const;

  const string& Name() ;

  int GetID( ) const;


  virtual int GetCredit(int out, int vc_begin, int vc_end ) const = 0;
  virtual int GetBuffer(int i) const = 0;

  int NumOutputs(){return _outputs;}
};

#endif
