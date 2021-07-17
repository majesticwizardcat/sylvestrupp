#pragma once

class MarabuObject;
enum class MarabuObjectType;
class Transaction;
class Block;

#include "core/constants.h"

#include <json.hpp>
#include <vector>
#include <string>
#include <map>

enum class MarabuObjectType {
	TRANSACTION, BLOCK
};

const std::string OJBECT_TYPE_TRANSACTION = "transaction";
const std::string OJBECT_TYPE_BLOCK = "block";

const std::string OBJECT_STR_TYPE = "type";
const std::string OBJECT_STR_INPUTS = "inputs";
const std::string OBJECT_STR_OUTPUTS = "outputs";
const std::string OBJECT_STR_TXID = "txid";
const std::string OBJECT_STR_INDEX = "index";
const std::string OBJECT_STR_OUTPOINT = "outpoint";
const std::string OBJECT_STR_SIG = "sig";
const std::string OBJECT_STR_PUBKEY = "pubkey";
const std::string OBJECT_STR_VALUE = "value";
const std::string OBJECT_STR_TXIDS = "txids";
const std::string OBJECT_STR_NONCE = "nonce";
const std::string OBJECT_STR_PREVID = "previd";
const std::string OBJECT_STR_CREATED = "created";
const std::string OBJECT_STR_T = "T";
const std::string OBJECT_STR_MINER = "miner";
const std::string OBJECT_STR_NOTE = "note";

const std::map<MarabuObjectType, std::string> OBJECT_TYPE_TO_STRING = {
	std::make_pair(MarabuObjectType::TRANSACTION, OJBECT_TYPE_TRANSACTION),
	std::make_pair(MarabuObjectType::BLOCK, OJBECT_TYPE_BLOCK),
};

class MarabuObject {
public:
	virtual ~MarabuObject() { }

	std::string asHash() const;
	virtual std::string asJson() const = 0;
	virtual MarabuObjectType getType() const = 0;
};

struct Outpoint {
	std::string txid;
	int index;
};

struct TransactionInput {
	Outpoint outpoint;
	std::string signature;
};

struct TransactionOutput {
	std::string publicKey;
	coin_t value;
};

class Transaction : public MarabuObject {
private:
	std::vector<TransactionInput> m_inputs;
	std::vector<TransactionOutput> m_outputs;

public:
	Transaction() { }

	std::string asJson() const;
	MarabuObjectType getType() const { return MarabuObjectType::TRANSACTION; }
};

class Block : public MarabuObject {
private:
	std::vector<std::string> m_txids;
	std::string m_nonce;
	std::string m_prevId;
	std::string m_target;
	std::string m_miner;
	std::string m_note;
	int m_created;

public:
	Block() { }
	Block(const std::vector<std::string> txids,
		const std::string& nonce,
		const std::string& prevId,
		const std::string& target,
		const std::string& miner,
		const std::string& note,
		int created)
		: m_txids(txids),
		m_nonce(nonce),
		m_prevId(prevId),
		m_created(created),
		m_target(target),
		m_miner(miner),
		m_note(note) { }

	std::string asJson() const;
	MarabuObjectType getType() const { return MarabuObjectType::BLOCK; }
};

const Block GENESIS_BLOCK(
	std::vector<std::string>(),
	"0000000000000000000000000000000000000000000000000000002634878840",
	"",
	"00000002af000000000000000000000000000000000000000000000000000000",
	"dionyziz",
	"The Economist 2021-06-20: Crypto-miners are probably to blame for the graphics-chip shortage",
	1624219079
); 

const std::string GENESIS_BLOCK_HASH = "00000000a420b7cefa2b7730243316921ed59ffe836e111ca3801f82a4f5360e";

void to_json(nlohmann::json& j, const TransactionOutput& trns);
void from_json(const nlohmann::json& j, TransactionOutput& trns);
void to_json(nlohmann::json& j, const TransactionInput& trns);
void from_json(const nlohmann::json& j, TransactionInput& trns);
void to_json(nlohmann::json& j, const Outpoint& out);
void from_json(const nlohmann::json& j, Outpoint& out);
