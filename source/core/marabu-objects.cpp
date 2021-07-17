#include "core/marabu-objects.h"
#include "crypto/hash.h"

std::string MarabuObject::asHash() const {
	return hashing::encodeHex(hashing::SHA256(asJson()));
}

std::string Transaction::asJson() const {
	nlohmann::json js {
		{OBJECT_STR_TYPE, OBJECT_TYPE_TO_STRING.at(getType())},
		{OBJECT_STR_INPUTS, m_inputs},
		{OBJECT_STR_OUTPUTS, m_outputs}
	};
	return js.dump();
}

std::string Block::asJson() const {
	nlohmann::json js = {
			{OBJECT_STR_TXIDS, m_txids},
			{OBJECT_STR_TYPE, OBJECT_TYPE_TO_STRING.at(getType())},
			{OBJECT_STR_MINER, m_miner},
			{OBJECT_STR_NOTE, m_note},
			{OBJECT_STR_CREATED, m_created},
			{OBJECT_STR_NONCE, m_nonce},
			{OBJECT_STR_T, m_target},
	};
	if (m_prevId.empty()) {
		js[OBJECT_STR_PREVID] = nullptr;
	}
	else {
		js[OBJECT_STR_PREVID] = m_prevId;
	}
	return js.dump();
}

void to_json(nlohmann::json& j, const TransactionOutput& trns) {
	j = {
		{OBJECT_STR_PUBKEY, trns.publicKey},
		{OBJECT_STR_VALUE, trns.value}
	};
}

void from_json(const nlohmann::json& j, TransactionOutput& trns) {
	trns.publicKey = j.at(OBJECT_STR_PUBKEY);
	trns.value = j.at(OBJECT_STR_VALUE);
}

void to_json(nlohmann::json& j, const TransactionInput& trns) {
	j = {
		{OBJECT_STR_OUTPOINT, trns.outpoint},
		{OBJECT_STR_SIG, trns.signature}
	};
}

void from_json(const nlohmann::json& j, TransactionInput& trns) {
	trns.outpoint = j.at(OBJECT_STR_OUTPOINT);
	trns.signature = j.at(OBJECT_STR_SIG);
}

void to_json(nlohmann::json& j, const Outpoint& out) {
	j = {
		{OBJECT_STR_TXID, out.txid},
		{OBJECT_STR_INDEX, out.index}
	};
}

void from_json(const nlohmann::json& j, Outpoint& out) {
	out.txid = j.at(OBJECT_STR_TXID);
	out.index = j.at(OBJECT_STR_INDEX);
}
