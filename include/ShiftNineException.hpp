class ShiftNineException: public std::exception {
	private:
		const char* m_message;

	public:
		/**
		 * Construct exception from static error string
		 *
		 * \param message - error string
		 */
		explicit ShiftNineException(const char* message);

		/**
		 * Return error message
		 *
		 * \return error message
		 */
		virtual const char* what() const throw();
};
